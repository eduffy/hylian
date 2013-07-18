#!/usr/bin/env python

import os
import sys
import gzip

import xml.etree.ElementTree as ET

NODE_BY_ID_PATH  = './graph/node[@id="%s"]'
FUNCTION_PATH    = './graph/node/type[@xlink:href="asg.gxl#Function"]/..'
NAME_ATTR_PATH   = './attr[@name="name"]/string'
PARENT_EDGE_PATH = './graph/edge[@to="%s"]/type[@xlink:href="asg.gxl#Contains"]/..'
RETURN_TYPE_PATH = './graph/edge[@from="%s"]/type[@xlink:href="asg.gxl#ReturnType"]/..'
BASE_TYPE_PATH   = './graph/edge[@from="%s"]/type[@xlink:href="asg.gxl#BaseType"]/..'
PARAM_DECL_PATH  = './graph/edge[@from="%s"]/type[@xlink:href="asg.gxl#ParameterDeclaration"]/..'
TYPEOF_PATH      = './graph/edge[@from="%s"]/type[@xlink:href="asg.gxl#TypeOf"]/..'


def resolveType(root, gxid):
  try:
    return resolveType.cache[gxid]
  except KeyError:
    pass

  el = root.find(NODE_BY_ID_PATH % gxid, namespaces=ns)
  assert el is not None
  #ET.dump(el)
  eltype = el.find('./type').attrib.values()[0].split('#')[1]  # ['xlink:href']
  #print eltype

  if eltype == 'BuiltinType':
    result = el.find(NAME_ATTR_PATH).text
  elif eltype == 'Class':
    # return el.find(NAME_ATTR_PATH).text
    result = getQualifiedName(root, el)
  elif eltype == 'ReferenceType':
    btype = root.find(BASE_TYPE_PATH % gxid, namespaces=ns)
    result = '%s&' % resolveType(root, btype.attrib['to'])
  elif eltype == 'PointerType':
    btype = root.find(BASE_TYPE_PATH % gxid, namespaces=ns)
    result = '%s*' % resolveType(root, btype.attrib['to'])
  elif eltype == 'ConstType':
    btype = root.find(BASE_TYPE_PATH % gxid, namespaces=ns)
    result = 'const %s' % resolveType(root, btype.attrib['to'])
  elif eltype == 'FunctionPointer':
    result = '(*)' # FIXME
  else:
    raise NotImplementedError

  resolveType.cache[gxid] = result
  return result
resolveType.cache = { }
  
  

def getQualifiedName(root, el):
  def _getQualifiedName(el):
    gxid = el.attrib['id']
    if gxid == 'global':
      return ""

    try:
      name   = el.find(NAME_ATTR_PATH).text
    except AttributeError:
      name = gxid
    pedge  = root.find(PARENT_EDGE_PATH % gxid, namespaces=ns)
    parent = root.find(NODE_BY_ID_PATH % pedge.attrib['from'], namespaces=ns)
    return '%s::%s' % (_getQualifiedName(parent), name)
  return _getQualifiedName(el)[2:]

def resolveFunction(root, el):
  gxid = el.attrib['id']
  print gxid
  #ET.dump(el)
  qname = getQualifiedName(root, el)

  # get return type
  returnTypeEdge = root.find(RETURN_TYPE_PATH % gxid, namespaces=ns)
  if returnTypeEdge is not None:
    returnType = '%s ' % resolveType(root, returnTypeEdge.attrib['to'])
  else:
    # constructors/destructors come here
    returnType = ''

  # iterate parameters
  parameters = [ ]
  for p in root.findall(PARAM_DECL_PATH % gxid, namespaces=ns):
    #print 'p=',
    #ET.dump(p)
    ptype = root.find(TYPEOF_PATH % p.attrib['to'], namespaces=ns)
    parameters.append(resolveType(root, ptype.attrib['to']))

  result = '%s%s(%s)' % (returnType, qname, ','.join(parameters))
  #print 'result="%s"' % result
  return result
  1/0
                 
  
  # function qualifiers

def findFunctions(root):
#  return [ resolveFunction(root, el)
#    for el in root.findall(FUNCTION_PATH, namespaces=ns) ]
    funs = root.findall(FUNCTION_PATH, namespaces=ns)
    for i,el in enumerate(funs):
      fstr = resolveFunction(root, el)
      print '%6d of %6d: %s' % (i+1,len(funs),fstr)
      

f    = gzip.open(sys.argv[1])
root = ET.parse(f)
ns   = {
  'xlink': "http://www.w3.org/1999/xlink",
}
print dir(root)

fun = findFunctions(root)
#x=root.findall('./graph/node/type[@xlink:href="asg.gxl#Function"]', namespaces=ns)
#print x
#print type(x)

"""
  <node id="Z00000000000A">
    <type xlink:href="asg.gxl#BuiltinType" />
    <attr name="name">
      <string>char</string>
    </attr>
    <attr name="size">
      <int>1</int>
    </attr>
  </node>"""

"""<edge from="global" to="Z000000000CA0">
    <type xlink:href="asg.gxl#Contains" />
  </edge>"""
