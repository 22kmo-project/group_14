const express = require('express');
const { getBalance } = require('../models/account_model');
const router = express.Router();
const account = require('../models/account_model');

router.post('/withdraw', 
function(request, response) {
  account.cashWithdraw(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      if (dbResult["affectedRows"] > 0) { // affectedRows = 1 if withdrawal was successful
        console.log("Success!");
        response.send(true);
      } else {
        console.log("Insufficient funds!");
        response.send(false);
      }
    }
  });
});

router.get('/:id?',
 function(request, response) {
  if (request.params.id) {
    account.getById(request.params.id, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult[0]);
      }
    });
  } else {
    account.getAll(function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  }
});


router.post('/', 
function(request, response) {
  account.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  account.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  account.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;