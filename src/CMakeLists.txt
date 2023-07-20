aux_source_directory(. APC)

add_executable(apc ${APC})

target_link_options(apc PRIVATE "-lm")
target_link_libraries(apc PRIVATE APC_PROJECT_OPTIONS APC_PROJECT_WARNINGS)
