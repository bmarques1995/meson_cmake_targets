app_sources = files(
    'code/runner.cc',
)

app = executable(
    'mesonapp',
    app_sources,

    include_directories : inc_dirs,
    cpp_args : cpp_public_args,
    link_with : lib,

    install : true,
    install_dir : get_option('bindir')
)

cmake.export_target(target: app, namespace: 'MesonLib')