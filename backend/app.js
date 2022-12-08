var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

const jwt = require('jsonwebtoken');

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

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);


app.use('/login', loginRouter);
app.use(authenticateToken);
app.use('/transactions', transactionsRouter);
app.use('/account', accountRouter);
app.use('/account_card', accountCardRouter);
app.use('/card', cardRouter);
app.use('/customer', customerRouter);

module.exports = app;
