# LGOS main meson.build file

project('stm32_test',
        'c',
        default_options: ['buildtype=release',
                          'warning_level=everything',
                          'werror=true',
                          'b_asneeded=false'],
        meson_version: '1.0.1',
        version: '0.1')

compiler = meson.get_compiler('c')
compiler_args = compiler.get_supported_arguments(['-pedantic',
                                                  '-ffreestanding',
                                                  '-Wa,--fatal-warnings'],
                                                 checked: 'require')

if not compiler.has_multi_link_arguments(['-nostdlib', '--entry=main'])
  error('Compiler for C does not support "-nostdlib"')
endif

if not compiler.has_multi_link_arguments(['-Wl,--fatal-warnings',
                                          '--specs=nosys.specs'])
  error('Compiler for C does not support "-Wl,--fatal-warnings"')
endif

add_project_arguments(compiler_args,
                      language: 'c')

add_project_link_arguments(['-nostdlib',
                            '-Wl,--fatal-warnings'],
                           language: 'c')

incdirs = include_directories('../cmsis/CMSIS/Core/Include',
                              '../cmsis/Device/ST/stm32f1/Include')

blink_elf = executable('blink.elf',
                       ['main.c', 'startup.c'],
                       include_directories: incdirs,
                       link_args: ['-T',
                                   meson.current_source_dir() + '/blink.ld'],
                       link_depends: 'blink.ld')
