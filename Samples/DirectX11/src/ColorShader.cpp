#include "ColorShader.h"
#include <d3dcompiler.h>
#include <iostream>

bool ColorShader::Initialize(ID3D11Device* d3dDevice, HWND hWnd)
{
	return InitializeShader(d3dDevice, hWnd, L"./assets/color.vs", L"./assets/color.ps");
}

void ColorShader::ShutDown()
{
	ShutDownShader();
}

bool ColorShader::Render(ID3D11DeviceContext* d3dDeviceContext, int indexCount)
{
	// bool result = SetShaderParameters(d3dDeviceContext, worldMatrix, viewMatrix, projectionMatrix);
	// if (!result)
	//	return false;

	RenderShader(d3dDeviceContext, indexCount);

	return true;
}

bool ColorShader::InitializeShader(ID3D11Device* d3dDevice, HWND hWnd, WCHAR* vsFileName, WCHAR* psFileName)
{
	HRESULT result;
	ID3D10Blob* errorMessage = nullptr;
	ID3D10Blob* vertexShaderBuffer = nullptr;
	ID3D10Blob* pixelShaderBuffer = nullptr;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Compile the vertex shader code.
	result = ::D3DCompileFromFile(vsFileName, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "ColorVertexShader", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0,
		&vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// if the shader failed to compile it should have writen something to the error message
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage);
		}
		else
		{
			std::cerr << "Compile VertexShader failed" << std::endl;
		}
		return false;
	}

	// Compile the pixel shader code.
	result = ::D3DCompileFromFile(psFileName, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "ColorPixelShader", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0,
		&pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// if the shader failed to compile it should have writen something to the error message
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage);
		}
		else
		{
			std::cerr << "Compile PixelShader failed" << std::endl;
		}
		return false;
	}

	// Create the vertex shader from the buffer
	result = d3dDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_VertexShader);
	if (FAILED(result))
	{
		std::cerr << "CreateVertexShader failed" << std::endl;
		return false;
	}

	// Create the pixel shader from the buffer
	result = d3dDevice->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_PixelShader);
	if (FAILED(result))
	{
		std::cerr << "CreatePixelShader failed" << std::endl;
		return false;
	}

	// Now setup the layout of the data that goes into the shader
	// This setup needs to match the VertexType structure in the Model and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout
	result = d3dDevice->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &m_Layout);
	if (FAILED(result))
	{
		std::cerr << "CreateInputLayout failed" << std::endl;
		return false;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	vertexShaderBuffer->Release();
	vertexShaderBuffer = nullptr;
	pixelShaderBuffer->Release();
	pixelShaderBuffer = nullptr;

	// Setup the description of the dynamic matrix constrant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = d3dDevice->CreateBuffer(&matrixBufferDesc, NULL, &m_MatrixBuffer);
	if (FAILED(result))
	{
		std::cerr << "CreateBuffer failed" << std::endl;
		return false;
	}

	return true;
}

void ColorShader::ShutDownShader()
{
	if (m_MatrixBuffer)
	{
		m_MatrixBuffer->Release();
		m_MatrixBuffer = nullptr;
	}

	if (m_Layout)
	{
		m_Layout->Release();
		m_Layout = nullptr;
	}

	if (m_PixelShader)
	{
		m_PixelShader->Release();
		m_PixelShader = nullptr;
	}

	if (m_VertexShader)
	{
		m_VertexShader->Release();
		m_VertexShader = nullptr;
	}
}

void ColorShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage)
{
	char* compileErrors;

	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	size_t bufferSize = errorMessage->GetBufferSize();

	// Write out the error message.
	for (size_t i = 0; i < bufferSize; i++)
	{
		std::cerr << compileErrors[i];
	}

	std::cerr << std::endl;

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;
}

bool ColorShader::SetShaderParameters(ID3D11DeviceContext* d3dDeviceContext, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;

	// Transpose the matrices to prepare them for the shader.
	worldMatrix = DirectX::XMMatrixTranspose(worldMatrix);
	viewMatrix = DirectX::XMMatrixTranspose(viewMatrix);
	projectionMatrix = DirectX::XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = d3dDeviceContext->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->World = worldMatrix;
	dataPtr->View = viewMatrix;
	dataPtr->Projection = projectionMatrix;

	// Unlock the constant buffer.
	d3dDeviceContext->Unmap(m_MatrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	d3dDeviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_MatrixBuffer);

	return true;
}

void ColorShader::RenderShader(ID3D11DeviceContext* d3dDeviceContext, int indexCount)
{
	// Set the vertex input layout.
	d3dDeviceContext->IASetInputLayout(m_Layout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	d3dDeviceContext->VSSetShader(m_VertexShader, NULL, 0);
	d3dDeviceContext->PSSetShader(m_PixelShader, NULL, 0);

	// Render the triangle.
	d3dDeviceContext->DrawIndexed(indexCount, 0, 0);
}
