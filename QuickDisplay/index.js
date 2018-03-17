var fileChoose = document.getElementById('myFile');
var graphDiv = document.getElementById('PLOT');

fileChoose.addEventListener("change", function () {
    var reader = new FileReader();

    reader.onload = function(){
      var data = reader.result;
      DrawPlot(JSON.parse(data));
    };
    reader.readAsText(fileChoose.files[0]);
  });

Plotly.newPlot(graphDiv, []);

function DrawPlot(data){
    Plotly.addTraces(graphDiv, data);
}



