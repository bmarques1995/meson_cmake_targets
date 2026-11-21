project(
    'MesonLib',
    'cpp',
    version : '0.0.1',
    default_options : [
        'cpp_std=c++20',
        'warning_level=3',
        'default_library=shared'
    ]
)

cmake = import('cmake')

project_name = 'MesonLib'
project_version = '0.0.1'

library_type = get_option('library_type')

inc_dirs = include_directories(
    'src/lib/code'
)

cpp_public_args = []
meson_lib_private_args = []

if library_type == 'shared'
    cpp_public_args += [
        '-DMESON_LIB_SHARED',
    ]
    meson_lib_private_args += [
        '-DMESON_LIB_EXPORTS'
    ]
endif

if host_machine.system() == 'windows'
    cpp_public_args += [
        '-DMESON_LIB_WINDOWS',
    ]
else
    cpp_public_args += [
        '-DMESON_LIB_UNIX',
    ]
endif

cmake.write_basic_package_version_file(name: meson.project_name(), version: meson.project_version())

subdir('src')
