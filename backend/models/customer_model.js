const db = require('../database');

const customer = {
  getById: function(id, callback) {
    return db.query('select * from customer where id_customer=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from customer', callback);
  },
  add: function(add_data, callback) {
    return db.query(
      'insert into customer (id_customer,name,address,phone_number) values(?,?,?,?)',
      [add_data.id_customer, add_data.name, add_data.address, add_data.phone_number],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from customer where id_customer=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    return db.query(
      'update customer set name=?, address=?, phone_number where id_customer=?',
      [update_data.name, udate_data.address, udate_data.phone_number, id],
      callback
    );
  }
};
module.exports = customer;