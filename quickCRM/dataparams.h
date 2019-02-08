#ifndef DATAPARAMS_H
#define DATAPARAMS_H
#include <Qt>


enum DataMethod {
    getHistory,
    getCalls,
    getQuery,
    getUsers,
    getOrgs,
    Authorization,
    Insertion
};

enum DataParams {
    FieldName,
    Expression
};

enum AsterRoles {
    aidRole = Qt::UserRole+1,
    acNumRole,
    acNameRole,
    aaNumRole,
    aaNameRole,
    adtRole,
    aunicIdRole,
    achStateRole,
    aorgUserRole,
    aunicID
};

enum UserRoles {
    uidRole = Qt::UserRole+1,
    uuRole,
    upwdRole,
    unumRole,
    uinLineRole
};

enum HistoryRoles {
    hidRole = Qt::UserRole+1,
    huRole,
    hdtRole,
    horgRole,
    hqRole,
    hfioRole,
    hnumRole,
    hcRole
};

enum OrgsRoles {
    orgPhoneRole = Qt::UserRole+1,
    orgNameRole,
    orgUserRole
};

enum QueryRoles {
    qidRole = Qt::UserRole+1,
    qtypeRole
};

enum RolesType {
    Aster,
    User,
    History,
    Orgs,
    Query
};

#endif // DATAPARAMS_H
