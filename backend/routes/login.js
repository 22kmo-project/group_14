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
              bcrypt.compare(pin,dbResult[0].pin, function(err,compareResult) {
                if(compareResult) {
                  console.log("Success");
                  const token = generateAccessToken({ username: id_card });
                  response.send(token);
                }
                else {
                    console.log("Wrong password");
                    console.log(dbResult[0].pin);
                    response.send(false);
                }			
              }
              );
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