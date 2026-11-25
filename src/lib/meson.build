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

inc_dirs_lib_log = [
    inc_dirs,
    inc_dirs_log,
]

inc_dirs_all = [
    inc_dirs,
    inc_dirs_log,
    inc_dirs_mod,
]

target_info = {}
export_list = []
export_log_list = []

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

if library_type == 'both'
    message('Both targets')
    export_list = meson_lib_public_args
    export_log_list = meson_log_public_args
    export_list_shared = meson_lib_public_args + meson_lib_public_shared_args
    export_log_list_shared = meson_log_public_args + meson_log_public_shared_args
    lib = both_libraries(
        'mesonlib',
        sources,
        include_directories : inc_dirs,
        cpp_static_args : meson_lib_public_args + meson_lib_private_args,
        cpp_shared_args : meson_lib_public_args + meson_lib_private_args + meson_lib_public_shared_args + meson_lib_private_shared_args,
        install : true
    )
    lib_log = both_libraries(
        'mesonlog',
        sources_log,
        include_directories : inc_dirs_lib_log,
        link_with: lib,
        cpp_static_args : meson_log_public_args + meson_log_private_args,
        cpp_shared_args : meson_log_public_args + meson_log_private_args + meson_log_public_shared_args + meson_log_private_shared_args,
        install : true
    )

    target_info = {
        'static': {
            'interface_include_dirs': ['include/mesonlib/code2'],
            'interface_compile_defs': export_list,
            'interface_compile_opts': [],
            'interface_link_opts': [],
            'interface_link_libraries': [],
            'interface_internal_dependencies': []
        },
        'shared': {
            'interface_include_dirs': ['include/mesonlib/code2'],
            'interface_compile_defs': export_list_shared,
            'interface_compile_opts': [],
            'interface_link_opts': [],
            'interface_link_libraries': [],
            'interface_internal_dependencies': []
        }
    }

    target_log_info = {
        'static': {
            'interface_include_dirs': ['include/mesonlib/code2'],
            'interface_compile_defs': export_log_list,
            'interface_compile_opts': [],
            'interface_link_opts': [],
            'interface_link_libraries': [],
            'interface_internal_dependencies': ['MesonLib::mesonlib_static']
        },
        'shared': {
            'interface_include_dirs': ['include/mesonlib/code2'],
            'interface_compile_defs': export_log_list_shared,
            'interface_compile_opts': [],
            'interface_link_opts': [],
            'interface_link_libraries': [],
            'interface_internal_dependencies': ['MesonLib::mesonlib']
        }
    }

    cmake.export_target(
        target: lib.get_shared_lib(),
        namespace: 'MesonLib',
        target_info: target_info['shared']
    )

    cmake.export_target(
        target: lib_log.get_shared_lib(),
        namespace: 'MesonLib',
        target_info: target_log_info['shared']
    )

    cmake.export_target(
        target: lib.get_static_lib(),
        namespace: 'MesonLib',
        target_suffix: '_static',
        target_info: target_info['static']
    )

    cmake.export_target(
        target: lib_log.get_static_lib(),
        namespace: 'MesonLib',
        target_suffix: '_static',
        target_info: target_log_info['static']
    )
else
    if library_type == 'shared'
        message('Shared target')
        export_list = meson_lib_public_args + meson_lib_public_shared_args
        export_log_list = meson_log_public_args + meson_log_public_shared_args
        #install_dir : shared_install_dir,
        lib = shared_library(
            'mesonlib',
            sources,
            include_directories : inc_dirs,
            cpp_args : meson_lib_public_args + meson_lib_public_shared_args + meson_lib_private_args + meson_lib_private_shared_args,
            install : true
        )
        lib_log = shared_library(
            'mesonlog',
            sources_log,
            include_directories : inc_dirs_lib_log,
            cpp_args : meson_log_public_args + meson_log_public_shared_args + meson_log_private_args + meson_log_private_shared_args,
            #install_dir : shared_install_dir,
            link_with: lib,
            install : true
        )
        target_info = {
            'interface_include_dirs': ['include/mesonlib/code'],
            'interface_compile_defs': export_list,
            'interface_compile_opts': [],
            'interface_link_opts': [],
            'interface_link_libraries': [],
        }

        target_log_info = {
            'interface_include_dirs': ['include/mesonlib/code2'],
            'interface_compile_defs': export_log_list,
            'interface_compile_opts': [],
            'interface_link_opts': [],
            'interface_link_libraries': [],
            'interface_internal_dependencies': ['MesonLib::mesonlib']
        }
    else
        message('Static target')
        export_list = meson_lib_public_args
        export_log_list = meson_log_public_args
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

        target_info = {
            'interface_include_dirs': ['include/mesonlib/code'],
            'interface_compile_defs': export_list,
            'interface_compile_opts': [],
            'interface_link_opts': [],
            'interface_link_libraries': [],
        }

        target_log_info = {
            'interface_include_dirs': ['include/mesonlib/code2'],
            'interface_compile_defs': export_log_list,
            'interface_compile_opts': [],
            'interface_link_opts': [],
            'interface_link_libraries': [],
            'interface_internal_dependencies': ['MesonLib::mesonlib']
        }
    endif

    cmake.export_target(
        target: lib,
        namespace: 'MesonLib',
        target_info: target_info
    )

    cmake.export_target(
        target: lib_log,
        namespace: 'MesonLib',
        target_info: target_log_info
    )
endif

lib_mod = shared_module(
    'mesonmod',
    files(
        'module/Hello.cc',
    ),
    include_directories : inc_dirs_all,
    cpp_args : meson_mod_public_args + meson_mod_private_args,
    install : true,
    link_with: lib_log,
)

target_mod_info = {
    'interface_include_dirs': ['include/mesonlib/module'],
    'interface_compile_defs': meson_mod_public_args,
    'interface_compile_opts': [],
    'interface_link_opts': [],
    'interface_link_libraries': [],
    'interface_internal_dependencies': ['MesonLib::mesonlog']
}

cmake.export_target(
    target: lib_mod,
    namespace: 'MesonLib',
    target_info: target_mod_info
)
