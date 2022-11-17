const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds = 10;

const card = {
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
    }
    
};
module.exports = card;