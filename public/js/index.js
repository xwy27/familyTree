$(function () {
  const OL_Action_Root = "http://localhost:8888";
  var options = {"closeOnOutsideClick": true};
  var tree = $('.tree');
  var dialogMsg = $('[data-remodal-id=modalMsg]').remodal(options);
  var dialogForm = $('[data-remodal-id=modalForm]').remodal(options);
  var Msg = $('#msg')[0]; 
  var genderLabel = $('.gender');
  var presentFunc = 0;
  var presentID = 0;

  var firstName = $('#firstName');
  var lastName = $('#lastName');
  var birthDay = $('#birthDay');
  var deadDay = $('#deadDay');

  Req_ajax({
    "func": 6
  });
  

  $('.input__field').focus(function () {
    $(this).parent().addClass('input__filled');
  });

  $('.input__field').blur(function () {
    if (this.value == "") {
      $(this).parent().removeClass('input__filled');
    }
  });

  genderLabel.click(function() {
    if (this.id == 'male')
      this.id = 'female';
    else
      this.id = 'male';
  });

  function clearInput() {
    firstName[0].value = '';
    lastName[0].value = '';
    birthDay[0].value = '';
    deadDay[0].value = '';
    $('.input__field').parent().removeClass('input__filled');
  }

  function dataSender() {
    if ($('.input__filled').length + (deadDay.parent()[0].className == 'input') != 4) {
      warning('You should fill every blank except deadday.');
      $(document).one('confirmation', '[data-remodal-id=modalMsg]', function() {
        dialogForm.open();
      });
      return;
    }
    var data = {
      "func": presentFunc,
      "id": presentID,
      "detail": JSON.stringify(getDetail())
    };
    clearInput();
    Req_ajax(data);
  }

  $(document).on('confirmation', '[data-remodal-id=modalForm]', dataSender);
  $(document).on('cancellation', '[data-remodal-id=modalForm]', function () {
    clearInput();
  });
  $(document).on('closed', '[data-remodal-id=modalForm]', function (e) {
    clearInput();
  });

  function getDetail() {
    return {
      "firstName": firstName[0].value,
      "lastName": lastName[0].value,
      "birthDay": birthDay[0].value,
      "deadDay": deadDay[0].value,
      "isMale": genderLabel[0].id == 'male'
    };
  }

  $('.tree span').click(function() {
    var data = {
      "func": 4,
      "id": this.id
    };
    Req_ajax(data, true);
  });
  

  $.contextMenu ({
    selector: 'span',
    callback: function (key, options) {
      switch(key) {
        case 'addParent':
          presentID = this[0].id;
          presentFunc = 0;
          dialogForm.open();
        break;
        
        case 'addBrother':
          presentID = this[0].id;
          presentFunc = 2;
          dialogForm.open();
        break;
        
        case 'addCouple':
          presentID = this[0].id;
          presentFunc = 1;
          dialogForm.open();
        break;
        
        case 'addChild':
          presentID = this[0].id;
          presentFunc = 3;
          dialogForm.open();
        break;
        
        case 'edit':
          var data = {
            "func": 4,
            "id": this[0].id
          };
          presentFunc = 7;
          presentID = this[0].id;
          Req_ajax(data, "info");
        break;
        
        case 'delete':
          var data = {
            "func": 5,
            "id": this[0].id
          };
          Req_ajax(data);
        break;
        
        case 'detail':
          var data = {
            "func": 4,
            "id": this[0].id
          };
          Req_ajax(data, true);
        break;
        
        case 'quit':
          window.close();
        break;

        case 'refresh':
          var data = {
            "func": 6
          };
          Req_ajax(data);
        break;

        case 'statics':
          warning('Total: ' + $('.tree span').length + 
            '<br>Men: ' + $('.Male').length + 
            '<br>Women: ' + $('.Female').length, "Statics Data");
        break;
         
        default:
        break;
      }
    },
    items: {
      "Add...": { name: "Add...", icon: "fa-plus",
        items: {
          "addParent": { name: "Parent", icon: "fa-user-plus"},
          "addBrother": { name: "Brother", icon: "fa-user-plus"},
          "addCouple": { name: "Couple", icon: "fa-user-plus"},
          "addChild": { name: "Child", icon: "fa-user-plus"}
        }
      },
      "detail": { name: "Detail", icon: "fa-info-circle"},
      "edit": { name: "Edit", icon: "fa-pencil-square"},
      "delete": { name: "Delete", icon: "delete" },
      "refresh": { name: "Refresh", icon: "fa-refresh"},
      "statics": { name: "Statics", icon: "fa-users"},
      "sep1": "---------",
      "quit": {
        name: "Quit", icon: 'context-menu-icon context-menu-icon-quit'
      },
      
    }
  });

  /* if success, send an array to the callback, which contains all the data needed */

  function warning(msg, title = "Notice") {
    Msg.innerHTML = msg;
    $('#noticeTitle')[0].textContent = title;
    dialogMsg.open();
  }

  function Req_ajax(dataIn, jump) {
    $.ajax({
      data: dataIn,
      url: OL_Action_Root + "/func",
      dataType: 'json',
      cache: false,
      timeout: 5000,
      type: "post",
      success: function (data) {
        console.log(data);
        if (data.isError) {
          warning(data.data);
        }
        else if (jump == undefined) {
          tree[0].innerHTML = data.data;
          $('.tree span').click(function() {
            var data = {
              "func": 4,
              "id": this.id
            };
            Req_ajax(data, true);
          }); 
        }
        else if(jump === true){
          var str = "";

          for (var i in data) {
            if (i == 'isMale'){
              str += "Gender: " + ((data[i] == true) ? "Male" : "Female");
            } 
            else{
              str = str + i + ": " + data[i] + "<br>";
            }
          }

          warning(str, "Detail");
        }
        else{
          firstName[0].value = data['firstName'];
          if (firstName[0].value != "") {
            firstName.parent().addClass('input__filled')
          }
          lastName[0].value = data['lastName'];
          if (lastName[0].value != "") {
            lastName.parent().addClass('input__filled')
          }
          birthDay[0].value = data['birthDay'];
          if (birthDay[0].value != "") {
            birthDay.parent().addClass('input__filled')
          }
          deadDay[0].value = data['deadDay'];
          if (deadDay[0].value != "") {
            deadDay.parent().addClass('input__filled')
          }
          genderLabel.id = (data['isMale'] ? "male" : "female");
          dialogForm.open();
        }
      },
      error: function (jqXHR, textStatus, errorThrown) {
        console.log(jqXHR);
      }
    });
  }

});