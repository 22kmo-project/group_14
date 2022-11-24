const db = require('../database');


const transactions = {
    getById: function (id, callback) {
        return db.query('select * from Transactions where id_transaction=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from Transactions', callback);
    },
    add: function (add_data, callback) {
            return db.query(
                'insert into Transactions (id_account, id_card, date, event, amount) values(?,?,?,?,?)',
                [add_data.id_account, add_data.id_card, add_data.date, add_data.event, add_data.amount],
                callback);
    },
    delete: function (id, callback) {
        return db.query('delete from Transactions where id_transaction=?', [id], callback);
    },
    update: function (id, update_data, callback) {
            return db.query(
                'update Transactions set id_account=?, id_card=? , date=?, event=?, amount=? where id_transaction=?',
                [update_data.id_account, update_data.id_card, update_data.date, update_data.event, update_data.amount, id],
                callback);
    }    
};
module.exports = transactions;