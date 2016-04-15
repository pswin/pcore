TEMPLATE = subdirs

SUBDIRS += lib
SUBDIRS += test

test.depends = lib
