/****************************************************************************
** Meta object code from reading C++ file 'updatetool.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../updatetool.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'updatetool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_updateTool[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      43,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      69,   11,   11,   11, 0x08,
     108,   11,   11,   11, 0x08,
     147,   11,   11,   11, 0x08,
     202,  181,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_updateTool[] = {
    "updateTool\0\0getVersionInfoFinishedSignal()\0"
    "getUpdateFinishedSignal()\0"
    "getVersionInfoFinished(QNetworkReply*)\0"
    "generateSecretFinished(QNetworkReply*)\0"
    "getUpdateFinished(QNetworkReply*)\0"
    "bytesRead,totalBytes\0"
    "updateDataReadProgress(qint64,qint64)\0"
};

void updateTool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        updateTool *_t = static_cast<updateTool *>(_o);
        switch (_id) {
        case 0: _t->getVersionInfoFinishedSignal(); break;
        case 1: _t->getUpdateFinishedSignal(); break;
        case 2: _t->getVersionInfoFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: _t->generateSecretFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->getUpdateFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->updateDataReadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData updateTool::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject updateTool::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_updateTool,
      qt_meta_data_updateTool, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &updateTool::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *updateTool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *updateTool::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_updateTool))
        return static_cast<void*>(const_cast< updateTool*>(this));
    return QObject::qt_metacast(_clname);
}

int updateTool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void updateTool::getVersionInfoFinishedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void updateTool::getUpdateFinishedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
