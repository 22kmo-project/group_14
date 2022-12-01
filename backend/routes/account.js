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
      if (dbResult[0][0]["success"] == 1) { // success returns 1 if account had enough balance and withdrawal was succesfull
        console.log(dbResult[0]);
        console.log("Success!\n");
        response.json(dbResult[0]);
      } else {
        console.log(dbResult[0]);
        console.log("Insufficient funds!\n");
        response.json(dbResult[0]);
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

router.post('/donation', 
function(request, response) {
  account.donation(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      if (dbResult["affectedRows"] > 0) { // affectedRows = 1 if donation was successful
        console.log("Success!");
        response.send(true);
      } else {
        console.log("Insufficient funds!");
        response.send(false);
      }
    }
  });
});

module.exports = router;