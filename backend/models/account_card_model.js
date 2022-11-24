const db = require('../database');


const account_card = {
    getById: function (id, callback) {
        return db.query('select * from Account_Card where id_account=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from Account_Card', callback);
    },
    add: function (add_data, callback) {
            return db.query(
                'insert into Account_Card (id_account, id_card) values(?,?)',
                [add_data.id_account_card, add_data.balance, add_data.id_customer, add_data.credit_limit],
                callback);
    },
    delete: function (id, callback) {
        return db.query('delete from Account_Card where id_account=?', [id], callback);
    },
	//Need to rework the update function to somehow differentiate between linked account and card since there can
	//be multiple instances of linked accounts or cards
    update: function (id, update_data, callback) {
            return db.query(
                'update Account_Card set id_account=?, id_card=? where id_account=?',
                [update_data.balance, update_data.id_customer, update_data.credit_limit, id],
                callback);
    }    
};
module.exports = account_card;