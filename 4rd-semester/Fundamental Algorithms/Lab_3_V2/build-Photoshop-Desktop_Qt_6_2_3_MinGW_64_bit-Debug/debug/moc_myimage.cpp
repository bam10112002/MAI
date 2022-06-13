/****************************************************************************
** Meta object code from reading C++ file 'myimage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Photoshop/Filters/myimage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myimage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyImage_t {
    const uint offsetsAndSize[18];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MyImage_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MyImage_t qt_meta_stringdata_MyImage = {
    {
QT_MOC_LITERAL(0, 7), // "MyImage"
QT_MOC_LITERAL(8, 8), // "RedShift"
QT_MOC_LITERAL(17, 0), // ""
QT_MOC_LITERAL(18, 10), // "GreenShift"
QT_MOC_LITERAL(29, 9), // "BlueShift"
QT_MOC_LITERAL(39, 2), // "BW"
QT_MOC_LITERAL(42, 7), // "Inverse"
QT_MOC_LITERAL(50, 11), // "ThresholdUp"
QT_MOC_LITERAL(62, 13) // "ThresholdDown"

    },
    "MyImage\0RedShift\0\0GreenShift\0BlueShift\0"
    "BW\0Inverse\0ThresholdUp\0ThresholdDown"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyImage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x0a,    1 /* Public */,
       3,    1,   59,    2, 0x0a,    3 /* Public */,
       4,    1,   62,    2, 0x0a,    5 /* Public */,
       5,    0,   65,    2, 0x0a,    7 /* Public */,
       6,    0,   66,    2, 0x0a,    8 /* Public */,
       7,    1,   67,    2, 0x0a,    9 /* Public */,
       8,    1,   70,    2, 0x0a,   11 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void MyImage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyImage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->RedShift((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->GreenShift((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->BlueShift((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->BW(); break;
        case 4: _t->Inverse(); break;
        case 5: _t->ThresholdUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->ThresholdDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MyImage::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MyImage.offsetsAndSize,
    qt_meta_data_MyImage,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MyImage_t
, QtPrivate::TypeAndForceComplete<MyImage, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *MyImage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyImage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyImage.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyImage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
