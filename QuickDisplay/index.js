var fileChoose = document.getElementById('myFile');
var graphDiv = document.getElementById('PLOT');

fileChoose.addEventListener("change", function () {
    var files = fileChoose.files;
    var reader = new FileReader();
    var counter = 0;
    reader.onloadend = function(){
      counter++;
      DrawPlot(JSON.parse(reader.result));
      if(counter < files.length)
      {
        reader.readAsText(files[counter]);
      }
    };
    reader.readAsText(files[0]);
  });

Plotly.newPlot(graphDiv, []);

function DrawPlot(data){
    Plotly.addTraces(graphDiv, data);
}

