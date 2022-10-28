/////////////
// GLOBALS //
/////////////
cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

//////////////
// TYPEDEFS //
//////////////
// POSITION works for vertex shaders and SV_POSITION works for pixel shaders while COLOR works for both.
// If you want more than one of the same type then you have to add a number to the end such as COLOR0, COLOR1, and so forth.
struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType ColorVertexShader(VertexInputType input)
{
    PixelInputType output;
    

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    // output.position = mul(input.position, worldMatrix);
    // output.position = mul(output.position, viewMatrix);
    // output.position = mul(output.position, projectionMatrix);
    output.position = input.position;
    
    // Store the input color for the pixel shader to use.
    output.color = input.color;
    
    return output;
}

