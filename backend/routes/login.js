const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const card = require('../models/card_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    console.log(request.body.id_card + request.body.pin);
    if(request.body.id_card && request.body.pin){
      const id_card = request.body.id_card;
      const pin = request.body.pin;
        card.checkPassword(id_card, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          }
          else{
            if (dbResult.length > 0) {
              card.checkIfCardLocked(id_card, function(dbError2, dbResult2) {
                if(dbError2) {
                  response.json(dbError2);
                } else {
                  console.log(dbResult2[0][0]["is_locked"]);
                  bcrypt.compare(pin,dbResult[0].pin, function(err,compareResult) {
                    if(compareResult && dbResult2[0][0]["is_locked"] == 0) { // is_locked == 0 means card is not locked
                      console.log("Success");
                      const token = generateAccessToken({ username: id_card });
                      response.send(token);
                    } 
                    else if(compareResult && dbResult2[0][0]["is_locked"] == 1) { // is_locked == 1 means card is locked
                      console.log("Card is locked");
                      response.send({ isLocked: 1 });
                    }
                    else {
                        console.log("Wrong password");
                        console.log(dbResult[0].pin);
                        card.updateWrongPinCounter(id_card, function(dbError, dbResult) {
                          if(dbError) {
                            response.json(dbError);
                          }
                        });
                        response.send(false);
                    }			
                  }
                  );
                }
              });
            }
            else{
              console.log("User does not exist");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("id_card or password missing");
      response.send(false);
    }
  }
);

function generateAccessToken(username) {
    dotenv.config();
    return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
  }
  

module.exports=router;