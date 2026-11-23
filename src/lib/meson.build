#pkg = import('pkgconfig')
#bar_dep = dependency('bar')
#lib = library('foo', dependencies : [bar])
#pkg.generate(lib)

cmake = import('cmake')

#mylib_dep = declare_dependency(
  #include_directories : include_directories('code'),
#)

#cmake.export_target(target: mylib_dep, namespace: 'MesonLib')

sources = files(
    'code/Math.cc',
)

sources_log = files(
    'code2/Log.cc',
)

inc_dirs_both = [
    inc_dirs,
    inc_dirs_log,
]

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
        cpp_args : meson_lib_public_args + meson_lib_public_shared_args + meson_lib_private_args + meson_lib_private_shared_args,
        install_dir : shared_install_dir,
        install : true
    )
    lib_log = shared_library(
        'mesonlog',
        sources_log,
        include_directories : inc_dirs_both,
        cpp_args : meson_log_public_args + meson_log_public_shared_args + meson_log_private_args + meson_log_private_shared_args,
        install_dir : shared_install_dir,
        link_with: lib,
        install : true
    )
else
    lib = static_library(
        'mesonlib',
        sources,
        include_directories : inc_dirs,
        cpp_args : meson_lib_public_args + meson_lib_private_args,
        install : true
    )
    lib_log = static_library(
        'mesonlog',
        sources_log,
        include_directories : inc_dirs_log,
        link_with: lib,
        cpp_args : meson_log_public_args + meson_log_private_args,
        install : true
    )
endif

install_headers(
    'code/Math.hh',
    'code/Exporter.hh',
    subdir : 'mesonlib/code'
)

install_headers(
    'code2/Log.hh',
    'code2/Exporter.hh',
    subdir : 'mesonlib/code2'
)

conf = configuration_data()
conf.set_quoted('MESONLIB_TARGETS_EXPORT_NAME', 'MesonLibTargets')

cmake.configure_package_config_file(
    name: 'MesonLib',
    input: 'cmake/config.meson.cmake.in',
    configuration: conf
)

cmake.export_target(
    target: lib,
    namespace: 'MesonLib',
    target_info: {
        'interface_include_dirs': ['include'],
        'interface_compile_defs': ['MY_LIBRARY'],
        'interface_compile_opts': ['-Wall'],
        'interface_link_opts': [],
        'interface_link_libraries': [],
    }
)

cmake.export_target(
    target: lib_log,
    namespace: 'MesonLib',
    target_info: {
        'interface_include_dirs': ['include'],
        'interface_compile_defs': ['MY_LIBRARY'],
        'interface_compile_opts': ['-Wall'],
        'interface_link_opts': [],
        'interface_link_libraries': [],
        'interface_internal_dependencies': ['MesonLib::mesonlib']
    }
)

