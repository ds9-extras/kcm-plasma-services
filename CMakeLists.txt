project(sddm-kcm)
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(PROJECT_VERSION "5.6.90")
set(QT_MIN_VERSION "5.4.0")
find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ECMInstallIcons)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets DBus)

find_package(KF5 REQUIRED COMPONENTS
    CoreAddons
    I18n
    XmlGui
    ConfigWidgets
    KIO
    Baloo
)

add_definitions(-DTRANSLATION_DOMAIN=\"kcm_plasmaservices\")

install(FILES kcm_plasmaservices.desktop DESTINATION ${CMAKE_INSTALL_KSERVICES5DIR})

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

