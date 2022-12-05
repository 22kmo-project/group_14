const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds = 10;

const card = {
    getNumberOfAccounts: function (id, callback) {
        return db.query('SELECT (SELECT COUNT(*) FROM account JOIN account_card ON account_card.id_account=account.id_account JOIN card ON card.id_card=account_card.id_card WHERE card.id_card=?) AS number_of_accounts', [id], callback); // Returns the number of accounts associated with the card, 1 = only debit account, 2 = debit and credit account.
    },
    getById: function (id, callback) {
        return db.query('select * from Card where id_card=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from Card', callback);
    },
    add: function (add_data, callback) {
        bcrypt.hash(add_data.pin, saltRounds, function (err, hashedPassword) {
            return db.query(
                'insert into Card (id_card, type, pin) values(?,?,?)',
                [add_data.id_card, add_data.type, hashedPassword],
                callback);
        });
    },
    delete: function (id, callback) {
        return db.query('delete from Card where id_card=?', [id], callback);
    },
    update: function (id, update_data, callback) {
        bcrypt.hash(update_data.pin, saltRounds, function (err, hashedPassword) {
            return db.query(
                'update Card set type=?, pin=? where id_card=?',
                [update_data.type, hashedPassword, id],
                callback);
        });
    },
    checkPassword: function(id_card, callback){
        return db.query('select pin from Card where id_card=?',[id_card],callback);
    },
	attachAccount: function(add_data, callback) {
		return db.query(
			'insert into Account_Card (id_account, id_card) values (?,?)',
			[add_data.id_account, add_data.id_card],
			callback);
    },
    accountCardById: function (id, callback) {
        return db.query('select * from Account_Card where id_account=?', [id], callback);
    }
};
module.exports = card;