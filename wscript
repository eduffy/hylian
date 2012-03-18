# vim:syn=python
# encoding: ISO8859-1

from glob import glob
import os
from subprocess import Popen
from subprocess import PIPE

APPNAME = 'hylian'
VERSION = '1.9.90'

def exec_cmd(cmd):
  return Popen(cmd.split(), stdout=PIPE).communicate()[0].strip()

def options(ctx):
  #ctx.load('clangxx', tooldir='waftools')
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

  #print conf.env.table


def build(bld):

  bld.program(source=glob('src/*.cpp'),
     target='hylian-c++', use='llvm libclang clang sqlite3')

  bld.program(source='experimental/libclang/main.cpp',
     target='libclangc-test', use='llvm libclang', install_path=None)

  bld.install_files('${PREFIX}/share/hylian', 'schemas/gxl-1.0.dtd')
  bld.install_files('${PREFIX}/share/hylian', glob('schemas/*.gxl'))

