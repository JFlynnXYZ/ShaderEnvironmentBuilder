#ifndef PARSER_H__
#define PARSER_H__
#include <unordered_map>
#include <iostream>
#include <ngl/ShaderLib.h>
#include <ngl/Shader.h>
#include <fstream>
#include <UniformData.h>

//------------------------------------------------------------------------------
/// @file ParserLib.h
/// @brief the parsing library, used to manage all the uniform data.
/// @author Adam Jonathan Ting
/// @version 1.0
/// @date 05/05/16
//------------------------------------------------------------------------------
class ParserLib
{

public:
  //----------------------------------------------------------------------------
  /// @brief ctor for our ParserLib
  //----------------------------------------------------------------------------
  ParserLib();
  //----------------------------------------------------------------------------
  /// @brief dtor for our ParserLib
  //----------------------------------------------------------------------------
  ~ParserLib();
  //----------------------------------------------------------------------------
  /// @brief finds number of active uniforms and stores the data in blocks
  ///        called uniformData. This then stores it in a list m_uniformList
  //----------------------------------------------------------------------------
  void initializeUniformData();
  //----------------------------------------------------------------------------
  /// @brief sets default values for the active uniforms
  //----------------------------------------------------------------------------
  void assignUniformValues();
  //----------------------------------------------------------------------------
  /// @brief assigns all appropriate values, locations, data types, names
  //----------------------------------------------------------------------------
  void assignAllData();
  //----------------------------------------------------------------------------
  /// @brief takes the list of uniforms and updates them onto the shader,
  ///        depending on the data type.
  /// @param[in] _shader an instance of the current shader
  //----------------------------------------------------------------------------
  void sendUniformsToShader(ngl::ShaderLib *_shader);
  //----------------------------------------------------------------------------
  /// @brief prints the uniform location, data type and names
  //----------------------------------------------------------------------------
  void printUniforms();
  //----------------------------------------------------------------------------
  /// @brief used to translate the data type name from a number into a name.
  ///        e.g. 35676 -> mat4
  /// The following section was originally written by Jon Macey:-
  /// Jon Macey. NCCA library NGL::ShaderProgram::printRegisteredUniforms
  /// [online]. [Accessed 01/10/16]. Available from:
  /// <https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/index.html>.
  /// @editor Adam Ting
  //----------------------------------------------------------------------------
  void uniformDataTypes();
  //----------------------------------------------------------------------------
  /// @brief exports the uniformData into a .txt file
  //----------------------------------------------------------------------------
  void exportUniforms();
  //----------------------------------------------------------------------------
  /// @brief used to store the number of active uniforms
  //----------------------------------------------------------------------------
  uint m_num;
  //----------------------------------------------------------------------------
  /// @brief used to store a list of pre-registered Uniform data types.
  //----------------------------------------------------------------------------
  std::unordered_map <std::string, UniformData*> m_registeredUniforms;
  //----------------------------------------------------------------------------
  /// @brief used to store a list of uniformData
  //----------------------------------------------------------------------------
  std::vector <UniformData*> m_uniformList;


};

#endif // PARSER_H
