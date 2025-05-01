/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== interface.html ==================
static const unsigned char temp_binary_data_0[] =
"<!DOCTYPE html>\n"
"<html>\n"
"<head>\n"
"  <title>CScope XY Oscilloscope</title>\n"
"  <style>\n"
"    body {\n"
"      margin: 0;\n"
"      padding: 0;\n"
"      background-color: #000000;\n"
"      overflow: hidden;\n"
"      font-family: Arial, sans-serif;\n"
"      height: 100%;\n"
"    }\n"
"    #oscilloscope {\n"
"      width: 100%;\n"
"      height: 100vh;\n"
"    }\n"
"    #controls {\n"
"      position: absolute;\n"
"      top: 10px;\n"
"      right: 10px;\n"
"      color: #00ff00;\n"
"      background: rgba(255, 0, 0, 0.5);\n"
"      padding: 10px;\n"
"      border-radius: 5px;\n"
"    }\n"
"\n"
"    /* WebKit slider styling */\n"
"    #controls input[type=range] {\n"
"      -webkit-appearance: none;\n"
"      width: 150px;\n"
"      background: transparent;\n"
"      margin: 0 5px;\n"
"    }\n"
"    #controls input[type=range]::-webkit-slider-runnable-track {\n"
"      width: 100%;\n"
"      height: 4px;\n"
"      background: #00ff00;\n"
"      border-radius: 2px;\n"
"    }\n"
"    #controls input[type=range]::-webkit-slider-thumb {\n"
"      -webkit-appearance: none;\n"
"      width: 12px;\n"
"      height: 12px;\n"
"      background: #00ff00;\n"
"      border-radius: 50%;\n"
"      margin-top: -4px; /* center thumb on the track */\n"
"    }\n"
"  </style>\n"
"</head>\n"
"<body>\n"
"<canvas id=\"oscilloscope\"></canvas>\n"
"<div id=\"controls\">\n"
"  <label>\n"
"    Persistence\n"
"    <input type=\"range\" id=\"persistence\" min=\"0\" max=\"1\" step=\"0.01\" value=\"0.8\">\n"
"  </label>\n"
"</div>\n"
"<script>\n"
"  const canvas = document.getElementById('oscilloscope');\n"
"  const ctx    = canvas.getContext('2d');\n"
"  const slider = document.getElementById('persistence');\n"
"  let persistence = parseFloat(slider.value);\n"
"\n"
"  slider.addEventListener('input', () => {\n"
"    persistence = parseFloat(slider.value);\n"
"  });\n"
"\n"
"  function resize() {\n"
"    canvas.width  = window.innerWidth;\n"
"    canvas.height = window.innerHeight;\n"
"  }\n"
"  window.addEventListener('resize', resize);\n"
"\n"
"  // Generates one demo circle frame and returns {left, right}\n"
"  function makeDemoPattern() {\n"
"    const t = Date.now() / 1000;\n"
"    const left = [], right = [];\n"
"    const S = 512;\n"
"    for (let i = 0; i < S; ++i) {\n"
"      const a = (i / S) * 2 * Math.PI;\n"
"      left .push(Math.sin(a * 3 + t));\n"
"      right.push(Math.sin(a * 2 + t * 0.7));\n"
"    }\n"
"    return { left, right };\n"
"  }\n"
"\n"
"  // The single render loop:\n"
"  function drawFrame() {\n"
"    // fade background by persistence\n"
"    ctx.fillStyle = `rgba(0,0,0,${1 - persistence})`;\n"
"    ctx.fillRect(0, 0, canvas.width, canvas.height);\n"
"\n"
"    // pick real data if it exists, otherwise make a fresh demo frame\n"
"    const data = window.latestOscilloscopeData || makeDemoPattern();\n"
"\n"
"    // draw the XY trace, skipping any zero\xe2\x80\x90pairs so we don't connect back to the center\n"
"    ctx.strokeStyle = '#00ff00';\n"
"    ctx.lineWidth   = 2;\n"
"    ctx.beginPath();\n"
"    const cx    = canvas.width  / 2;\n"
"    const cy    = canvas.height / 2;\n"
"    const scale = Math.min(canvas.width, canvas.height) * 0.4;\n"
"    const L     = data.left;\n"
"    const R     = data.right;\n"
"    const n     = Math.min(L.length, R.length);\n"
"\n"
"    let started = false;\n"
"    for (let i = 0; i < n; ++i) {\n"
"      const x = cx + L[i] * scale;\n"
"      const y = cy + R[i] * scale;\n"
"\n"
"      // if both channels are zero, lift the pen\n"
"      if (L[i] === 0 && R[i] === 0) {\n"
"        started = false;\n"
"        continue;\n"
"      }\n"
"\n"
"      if (!started) {\n"
"        ctx.moveTo(x, y);\n"
"        started = true;\n"
"      } else {\n"
"        ctx.lineTo(x, y);\n"
"      }\n"
"    }\n"
"    ctx.stroke();\n"
"\n"
"    requestAnimationFrame(drawFrame);\n"
"  }\n"
"\n"
"  window.addEventListener('load', () => {\n"
"    resize();\n"
"    // clear any old data\n"
"    window.latestOscilloscopeData = null;\n"
"    // kick off the loop\n"
"    requestAnimationFrame(drawFrame);\n"
"  });\n"
"</script>\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"</body>\n"
"</html>";

const char* interface_html = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0xba16aef1:  numBytes = 3564; return interface_html;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "interface_html"
};

const char* originalFilenames[] =
{
    "interface.html"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
