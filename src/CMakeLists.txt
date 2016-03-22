set(SERVICES
    akonadiservice.cpp
    balooservice.cpp
    krunnerservice.cpp
    )

set(PLASMA_SERVICES_KCM
    plasmaserviceskcm.cpp
    ${SERVICES}
)

add_executable(plasma_services_test test.cpp ${SERVICES})

#
# set(SDDM_KCM_UI
#     ui/themeconfig.ui
#     ui/advanceconfig.ui)

# ki18n_wrap_ui(PLASMA_SERVICES_KCM ${SDDM_KCM_UI})
add_library(kcm_plasmaservices MODULE ${PLASMA_SERVICES_KCM})
target_compile_definitions(kcm_plasmaservices PRIVATE -DPROJECT_VERSION="${PROJECT_VERSION}")

target_link_libraries(kcm_plasmaservices
    Qt5::Widgets
    Qt5::DBus
    KF5::I18n
    KF5::ConfigWidgets
    KF5::KIOWidgets
    KF5::Baloo
)
target_link_libraries(plasma_services_test
    Qt5::Widgets
    Qt5::DBus
    KF5::I18n
    KF5::ConfigWidgets
    KF5::KIOWidgets
    KF5::Baloo
)

install(TARGETS kcm_plasmaservices DESTINATION ${CMAKE_INSTALL_PLUGINDIR})


