/****************************************************************************
** Meta object code from reading C++ file 'Validator.h'
**
** Created: Tue Mar 30 13:30:25 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Validator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Validator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Validator[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      19,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   38,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Validator[] = {
    "Validator\0\0message\0validated(QString)\0"
    "vec\0validate(InitVector)\0"
};

const QMetaObject Validator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Validator,
      qt_meta_data_Validator, 0 }
};

const QMetaObject *Validator::metaObject() const
{
    return &staticMetaObject;
}

void *Validator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Validator))
        return static_cast<void*>(const_cast< Validator*>(this));
    return QObject::qt_metacast(_clname);
}

int Validator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: validated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: validate((*reinterpret_cast< InitVector(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Validator::validated(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
