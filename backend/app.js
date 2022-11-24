var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

require("dotenv").config();

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');

var accountRouter = require('./routes/account');
var accountCardRouter = require('./routes/account_card');
var cardRouter = require('./routes/card');
var customerRouter = require('./routes/customer');
var loginRouter = require('./routes/login');
var transactionsRouter = require('./routes/transactions');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);

app.use('/account', accountRouter);
app.use('/account_card', accountCardRouter);
app.use('/card', cardRouter);
app.use('/customer', customerRouter);
app.use('/login', loginRouter);
app.use('/transactions', transactionsRouter);

module.exports = app;
