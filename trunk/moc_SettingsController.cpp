/****************************************************************************
** Meta object code from reading C++ file 'SettingsController.h'
**
** Created: Tue Apr 6 14:52:03 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "SettingsController.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingsController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SettingsController[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      32,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SettingsController[] = {
    "SettingsController\0\0startGame()\0"
    "disconnected()\0disconnect()\0"
};

const QMetaObject SettingsController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SettingsController,
      qt_meta_data_SettingsController, 0 }
};

const QMetaObject *SettingsController::metaObject() const
{
    return &staticMetaObject;
}

void *SettingsController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsController))
        return static_cast<void*>(const_cast< SettingsController*>(this));
    return QObject::qt_metacast(_clname);
}

int SettingsController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: startGame(); break;
        case 1: disconnected(); break;
        case 2: disconnect(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SettingsController::startGame()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SettingsController::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
