/****************************************************************************
** Meta object code from reading C++ file 'InitDialog.h'
**
** Created: Tue Mar 30 13:30:26 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "InitDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InitDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InitDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   11,   11,   11, 0x0a,
      61,   53,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_InitDialog[] = {
    "InitDialog\0\0vec\0dialogOK(InitVector)\0"
    "buttonClicked()\0message\0validated(QString)\0"
};

const QMetaObject InitDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_InitDialog,
      qt_meta_data_InitDialog, 0 }
};

const QMetaObject *InitDialog::metaObject() const
{
    return &staticMetaObject;
}

void *InitDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InitDialog))
        return static_cast<void*>(const_cast< InitDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int InitDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dialogOK((*reinterpret_cast< InitVector(*)>(_a[1]))); break;
        case 1: buttonClicked(); break;
        case 2: validated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void InitDialog::dialogOK(InitVector _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
