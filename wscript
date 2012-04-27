# vim:syn=python
# encoding: ISO8859-1

from glob import glob
import os, sys
from subprocess import Popen
from subprocess import PIPE

APPNAME = 'hylian'
VERSION = '1.9.90'

def exec_cmd(cmd):
  return Popen(cmd.split(), stdout=PIPE).communicate()[0].strip()

def options(ctx):
  ctx.load('compiler_c')
  ctx.load('compiler_cxx')
  ctx.load('tex')

def check_version(conf):
  version = exec_cmd('gcc -dumpversion')
  conf.env.DEFINES.append('GCC_VERSION="%s"' % version)
  conf.msg('Checking c++ version', version)

def check_machine(conf):
  machine = exec_cmd('gcc -dumpmachine')
  conf.env.DEFINES.append('GCC_MACHINE="%s"' % machine)
  conf.msg('Checking c++ machine', machine)

def check_ld_library_path(conf):
  libvar = 'LD_LIBRARY_PATH'
  if sys.platform == 'darwin':
    libvar = 'DYLD_LIBRARY_PATH'
  conf.start_msg('Checking $%s' % libvar)
  libdir = exec_cmd('llvm-config --libdir')
  llp = os.environ.get(libvar,'').split(':')
  if libdir in llp:
     conf.end_msg('yes')
  else:
     conf.end_msg('no')
     conf.fatal("Add the directory `%s' to your $%s variable" % (libdir, libvar))

def configure(conf):
  conf.env.DEFINES = [ ]
  conf.msg('Setting prefix to', os.path.expanduser(conf.options.prefix))
  conf.load('compiler_c')
  conf.load('compiler_cxx')
  check_version(conf)
  check_machine(conf)
  conf.load('tex')

  # llvm/libclang/clang checks
  conf.check_cfg(path='llvm-config', package='', uselib_store='llvm',
    args='--cxxflags --ldflags --libs')
  check_ld_library_path(conf)
  conf.check(lib='clang',              uselib_store='libclang', uselib='llvm')
  conf.check(lib='clangIndex',         uselib_store='clang', uselib='llvm')
  conf.check(lib='clangFrontend',      uselib_store='clang', uselib='llvm')
  conf.check(lib='clangSerialization', uselib_store='clang', uselib='llvm')
  conf.check(lib='clangLex',           uselib_store='clang', uselib='llvm')
  conf.check(lib='clangDriver',        uselib_store='clang', uselib='llvm')
  conf.check(lib='clangParse',         uselib_store='clang', uselib='llvm')
  conf.check(lib='clangSema',          uselib_store='clang', uselib='llvm')
  conf.check(lib='clangBasic',         uselib_store='clang', uselib='llvm')
  conf.check(lib='clangAnalysis',      uselib_store='clang', uselib='llvm')
  conf.check(lib='clangAST',           uselib_store='clang', uselib='llvm')

  conf.check(header_name='sqlite3.h')
  conf.check(header_name='sqlite3ext.h', mandatory=False)
  conf.check(lib='sqlite3', uselib_store='sqlite3')

  conf.check(header_name='expat.h')
  conf.check(lib='expat', uselib_store='expat')

def build(bld):

  bld.program(source=glob('src/*.cpp'),
     target='bin/hylian-c++', use='llvm libclang clang sqlite3')

  bld.program(source='experimental/libclang/main.cpp',
     target='libclangc-test', use='llvm libclang', install_path=None)

  bld.program(source=glob('experimental/callgraph/*.cpp'),
     target='callgraph', use='llvm libclang clang', install_path=None)

  for gxl in glob('schemas/*.gxl'):
    bgxl = os.path.basename(gxl)
    bld(rule='cp ${SRC} ${TGT}', source=gxl,
        target=os.path.join('share/hylian', bgxl), install_path=None)
    bld.install_files('${PREFIX}/share/hylian', os.path.join('build/share/hylian',bgxl))

