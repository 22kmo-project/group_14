const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'group_14',
  password: 'netpass',
  database: 'banksimul'
});
module.exports = connection;