set(PLASMA_SERVICES_KCM
    plasmaserviceskcm.cpp
)
#
# set(SDDM_KCM_UI
#     ui/themeconfig.ui
#     ui/advanceconfig.ui)

# ki18n_wrap_ui(PLASMA_SERVICES_KCM ${SDDM_KCM_UI})
add_library(kcm_plasmaservices MODULE ${PLASMA_SERVICES_KCM})
target_compile_definitions(kcm_plasmaservices PRIVATE -DPROJECT_VERSION="${PROJECT_VERSION}")

target_link_libraries(kcm_plasmaservices
    Qt5::Widgets
    KF5::I18n
    KF5::ConfigWidgets
    KF5::KIOWidgets
)
install(TARGETS kcm_plasmaservices DESTINATION ${CMAKE_INSTALL_PLUGINDIR})


