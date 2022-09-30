add_library(oingo-logging INTERFACE)

target_include_directories(oingo-logging INTERFACE ${PROJECT_SOURCE_DIR}/src)

add_library(Oingo::Logging ALIAS oingo-logging)
