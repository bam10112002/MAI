/****************************************************************************
** Meta object code from reading C++ file 'otherblock.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Photoshop/VisualBLocks/otherblock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'otherblock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OtherBlock_t {
    const uint offsetsAndSize[16];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_OtherBlock_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_OtherBlock_t qt_meta_stringdata_OtherBlock = {
    {
QT_MOC_LITERAL(0, 10), // "OtherBlock"
QT_MOC_LITERAL(11, 14), // "inverseClicked"
QT_MOC_LITERAL(26, 0), // ""
QT_MOC_LITERAL(27, 9), // "wbClicked"
QT_MOC_LITERAL(37, 15), // "beautifyClicked"
QT_MOC_LITERAL(53, 18), // "inverseClickedSlot"
QT_MOC_LITERAL(72, 13), // "wbClickedSlot"
QT_MOC_LITERAL(86, 19) // "beautifyClickedSlot"

    },
    "OtherBlock\0inverseClicked\0\0wbClicked\0"
    "beautifyClicked\0inverseClickedSlot\0"
    "wbClickedSlot\0beautifyClickedSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OtherBlock[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,
       3,    0,   51,    2, 0x06,    2 /* Public */,
       4,    0,   52,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   53,    2, 0x0a,    4 /* Public */,
       6,    0,   54,    2, 0x0a,    5 /* Public */,
       7,    0,   55,    2, 0x0a,    6 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OtherBlock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OtherBlock *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->inverseClicked(); break;
        case 1: _t->wbClicked(); break;
        case 2: _t->beautifyClicked(); break;
        case 3: _t->inverseClickedSlot(); break;
        case 4: _t->wbClickedSlot(); break;
        case 5: _t->beautifyClickedSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OtherBlock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OtherBlock::inverseClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OtherBlock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OtherBlock::wbClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (OtherBlock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OtherBlock::beautifyClicked)) {
                *result = 2;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject OtherBlock::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_OtherBlock.offsetsAndSize,
    qt_meta_data_OtherBlock,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_OtherBlock_t
, QtPrivate::TypeAndForceComplete<OtherBlock, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *OtherBlock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OtherBlock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OtherBlock.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int OtherBlock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void OtherBlock::inverseClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void OtherBlock::wbClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void OtherBlock::beautifyClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
