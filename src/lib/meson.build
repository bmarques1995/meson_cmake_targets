#pkg = import('pkgconfig')
#bar_dep = dependency('bar')
#lib = library('foo', dependencies : [bar])
#pkg.generate(lib)

cmake = import('cmake')

sources = files(
    'code/Math.cc',
)

if host_machine.system() == 'windows'
    shared_install_dir = get_option('bindir')
else
    shared_install_dir = get_option('libdir')
endif

if library_type == 'shared'
    lib = shared_library(
        'mesonlib',
        sources,
        include_directories : inc_dirs,
        cpp_args : cpp_public_args + meson_lib_private_args,
        install_dir : shared_install_dir,
        install : true
    )
else
    lib = static_library(
        'mesonlib',
        sources,
        include_directories : inc_dirs,
        cpp_args : cpp_public_args + meson_lib_private_args,
        install : true
    )
endif

install_headers(
    'code/Math.hh',
    'code/Exporter.hh',
    subdir : 'mesonlib/code'
)

cmake = import('cmake')

conf = configuration_data()
conf.set_quoted('MESONLIB_TARGETS_EXPORT_NAME', 'MesonLibTargets')

cmake.configure_package_config_file(
    name: 'MesonLib',
    input: 'cmake/config.meson.cmake.in',
    configuration: conf
)

cmake.export_target(target: lib, namespace: 'MesonLib')