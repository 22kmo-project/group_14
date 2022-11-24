const db = require('../database');


const account = {
    getById: function (id, callback) {
        return db.query('select * from Account where id_account=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from Account', callback);
    },
    add: function (add_data, callback) {
            return db.query(
                'insert into Account (id_account, balance, id_customer, credit_limit) values(?,?,?,?)',
                [add_data.id_account, add_data.balance, add_data.id_customer, add_data.credit_limit],
                callback);
    },
    delete: function (id, callback) {
        return db.query('delete from Account where id_account=?', [id], callback);
    },
    update: function (id, update_data, callback) {
            return db.query(
                'update Account set balance=?, id_customer=?, credit_limit=? where id_account=?',
                [update_data.balance, update_data.id_customer, update_data.credit_limit, id],
                callback);
    }    
};
module.exports = account;