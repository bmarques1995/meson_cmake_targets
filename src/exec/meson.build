app_sources = files(
    'code/runner.cc',
)

inc_dirs_both = [
    inc_dirs,
    inc_dirs_log,
]

app = executable(
    'mesonapp',
    app_sources,

    include_directories : inc_dirs_both,
    cpp_args : meson_lib_public_args + meson_log_public_args,
    link_with : [lib, lib_log],
    install : true,
    install_dir : get_option('bindir')
)

cmake.export_target(
    target: app,
    namespace: 'MesonLib',
    target_info: {
        'interface_internal_dependencies': ['MesonLib::mesonlib', 'MesonLib::mesonlog']
    }
)