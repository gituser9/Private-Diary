TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    PrivateDiaryCore \
    PrivateDiaryDesktop \
    PrivateDiaryMobile

PrivateDiaryDesktop.depends = PrivateDiaryCore
#PrivateDiaryMobile.depends = PrivateDiaryCore
