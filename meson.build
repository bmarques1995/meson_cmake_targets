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
    'src/lib/code',
)

inc_dirs_log = include_directories(
    'src/lib/code2',
)

inc_dirs_mod = include_directories(
    'src/lib/module',
)

meson_lib_public_args = []
meson_lib_private_args = []
meson_log_public_args = []
meson_log_private_args = []

meson_lib_public_shared_args = [
    '-DMESON_LIB_SHARED',
]
meson_lib_private_shared_args = [
    '-DMESON_LIB_EXPORTS'
]
meson_log_public_shared_args = [
    '-DMESON_LOG_SHARED',
]
meson_log_private_shared_args = [
    '-DMESON_LOG_EXPORTS'
]

meson_mod_public_args = []
meson_mod_private_args = [
    '-DMESON_MOD_EXPORTS'
]

if host_machine.system() == 'windows'
    meson_lib_public_args += [
        '-DMESON_LIB_WINDOWS',
    ]
    meson_log_public_args += [
        '-DMESON_LOG_WINDOWS',
    ]
    meson_mod_public_args += [
        '-DMESON_MOD_WINDOWS',
    ]
else
    meson_lib_public_args += [
        '-DMESON_LIB_UNIX',
    ]
    meson_log_public_args += [
        '-DMESON_LOG_UNIX',
    ]
    meson_mod_public_args += [
        '-DMESON_MOD_UNIX',
    ]
endif

cmake.write_basic_package_version_file(
    name: meson.project_name(),
    version: meson.project_version()
)

conf = configuration_data()
conf.set('MESONLIB_TARGETS_EXPORT_NAME', 'MesonLibTargets')

cmake.configure_package_config_file(
    name: 'MesonLib',
    input: 'cmake/config.cmake.in',
    configuration: conf
)

subdir('src')
