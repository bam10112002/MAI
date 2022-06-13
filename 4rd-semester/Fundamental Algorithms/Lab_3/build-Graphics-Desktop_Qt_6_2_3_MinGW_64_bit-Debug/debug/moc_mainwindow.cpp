/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Graphics/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[34];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 15), // "ShowAboutDialog"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 16), // "ShowAuthorDialog"
QT_MOC_LITERAL(45, 14), // "ComboBoxChange"
QT_MOC_LITERAL(60, 4), // "text"
QT_MOC_LITERAL(65, 16), // "RedSliderChanged"
QT_MOC_LITERAL(82, 18), // "GreenSliderChanged"
QT_MOC_LITERAL(101, 17), // "BlueSliderChanged"
QT_MOC_LITERAL(119, 14), // "UpLimitChanged"
QT_MOC_LITERAL(134, 18), // "BottomLimitChanged"
QT_MOC_LITERAL(153, 11), // "InverseSlot"
QT_MOC_LITERAL(165, 14), // "WhiteBlackSlot"
QT_MOC_LITERAL(180, 12), // "BeautifySlot"
QT_MOC_LITERAL(193, 7), // "LogSlot"
QT_MOC_LITERAL(201, 9), // "PowerSlot"
QT_MOC_LITERAL(211, 9) // "PartsSlot"

    },
    "MainWindow\0ShowAboutDialog\0\0"
    "ShowAuthorDialog\0ComboBoxChange\0text\0"
    "RedSliderChanged\0GreenSliderChanged\0"
    "BlueSliderChanged\0UpLimitChanged\0"
    "BottomLimitChanged\0InverseSlot\0"
    "WhiteBlackSlot\0BeautifySlot\0LogSlot\0"
    "PowerSlot\0PartsSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x08,    1 /* Private */,
       3,    0,   99,    2, 0x08,    2 /* Private */,
       4,    1,  100,    2, 0x08,    3 /* Private */,
       6,    1,  103,    2, 0x08,    5 /* Private */,
       7,    1,  106,    2, 0x08,    7 /* Private */,
       8,    1,  109,    2, 0x08,    9 /* Private */,
       9,    1,  112,    2, 0x08,   11 /* Private */,
      10,    1,  115,    2, 0x08,   13 /* Private */,
      11,    0,  118,    2, 0x08,   15 /* Private */,
      12,    0,  119,    2, 0x08,   16 /* Private */,
      13,    0,  120,    2, 0x08,   17 /* Private */,
      14,    0,  121,    2, 0x08,   18 /* Private */,
      15,    0,  122,    2, 0x08,   19 /* Private */,
      16,    0,  123,    2, 0x08,   20 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ShowAboutDialog(); break;
        case 1: _t->ShowAuthorDialog(); break;
        case 2: _t->ComboBoxChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->RedSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->GreenSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->BlueSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->UpLimitChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->BottomLimitChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->InverseSlot(); break;
        case 9: _t->WhiteBlackSlot(); break;
        case 10: _t->BeautifySlot(); break;
        case 11: _t->LogSlot(); break;
        case 12: _t->PowerSlot(); break;
        case 13: _t->PartsSlot(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
