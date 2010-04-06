/****************************************************************************
** Meta object code from reading C++ file 'SettingsDialog.h'
**
** Created: Tue Apr 6 14:52:01 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "SettingsDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SettingsDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      29,   15,   15,   15, 0x05,
      49,   41,   15,   15, 0x05,
      79,   70,   15,   15, 0x05,
     108,  100,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     128,   15,   15,   15, 0x0a,
     143,   15,   15,   15, 0x0a,
     167,   15,   15,   15, 0x0a,
     183,   15,   15,   15, 0x0a,
     199,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SettingsDialog[] = {
    "SettingsDialog\0\0disconnect()\0startGame()\0"
    "newName\0nameChanged(QString)\0newColor\0"
    "colorChanged(quint8)\0newTeam\0"
    "teamChanged(quint8)\0showSettings()\0"
    "hideSettingsAndSwitch()\0cancelClicked()\0"
    "createClicked()\0reload()\0"
};

const QMetaObject SettingsDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SettingsDialog,
      qt_meta_data_SettingsDialog, 0 }
};

const QMetaObject *SettingsDialog::metaObject() const
{
    return &staticMetaObject;
}

void *SettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsDialog))
        return static_cast<void*>(const_cast< SettingsDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int SettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: disconnect(); break;
        case 1: startGame(); break;
        case 2: nameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: colorChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 4: teamChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 5: showSettings(); break;
        case 6: hideSettingsAndSwitch(); break;
        case 7: cancelClicked(); break;
        case 8: createClicked(); break;
        case 9: reload(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void SettingsDialog::disconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SettingsDialog::startGame()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SettingsDialog::nameChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SettingsDialog::colorChanged(quint8 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SettingsDialog::teamChanged(quint8 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
