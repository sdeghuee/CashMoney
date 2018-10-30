var ss = SpreadsheetApp.getActiveSpreadsheet();
var sheet = ss.getSheets()[0];

function myFunction() {
}

function doGet(e){
  sheet.getRange("A3").setValue("wtf");
  var bps = sheet.getRange("A2").getValue();
  return ContentService.createTextOutput(JSON.stringify(bps));
}

function doPost(e){
  sheet.getRange("A4").setValue("Helloworld!");
}
