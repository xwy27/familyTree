var fs = require('fs');
var familyTree = require('./build/Release/familyTree');
var express = require('express');
var bodyParser = require('body-parser');
var app = express();
var urlencodedParser = bodyParser.urlencoded({ extended: false });

app.use(express.static('../public'));

app.get("/", function(req, res){
  res.status(200).type('html');
  fs.readFile('../public/html/index.html', function(err, data) {
    if (err) {
      console.log('Error loading home page.');
      res.end();
      return;
    }
    res.end(data);
  })
  console.log('Page visited.');
});

app.post('/func', urlencodedParser, function(req, res) {
  var data = req.body;
  console.log('Data received: ');
  console.log(data);
  
  switch(data.func) {
    case '0':case '1':
    case '2':case '3':
      var detail = JSON.parse(data.detail);
      var result = familyTree(data.func, detail['firstName'],
        detail['lastName'], detail['birthDay'], detail['deadDay'],
        detail['isMale'], data.id);
      console.log('Finished!');
      console.log(result);
      res.status(200).type('json').json(result).end();
    break;
    case '4':
      var result = familyTree(data.func, data.id);
      console.log('Finished!');
      console.log(result);
      res.status(200).type('json').json(result).end();
    break;

    case '5':
      var result = familyTree(data.func, data.id);
      console.log('Finished!');
      console.log(result);
      res.status(200).type('json').json(result).end();
    break;

    case '6':
      var result = familyTree(data.func);
      console.log('Finished!');
      console.log(result);
      res.status(200).type('json').json(result).end();
    break;

    case '7':
      var detail = JSON.parse(data.detail);
      var result = familyTree(data.func, detail['firstName'],
        detail['lastName'], detail['birthDay'], detail['deadDay'],
        detail['isMale'], data.id);
      console.log('Finished!');
      console.log(result);
      res.status(200).type('json').json(result).end();
    break;
  }
  
});

var server = app.listen(8888, function () {
  console.log('Listening...');
});