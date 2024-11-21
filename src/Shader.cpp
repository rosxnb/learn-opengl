#include <Shader.hpp>

#include <fstream>
#include <sstream>
#include <iostream>


Shader::Shader(std::string_view const& path_vertex, std::string_view const& path_fragment)
{
    std::string code_vertex = read_file(path_vertex);
    std::string code_fragment = read_file(path_fragment);

    vso_id      = compile_shader(GL_VERTEX_SHADER, code_vertex.data());
    fso_id      = compile_shader(GL_FRAGMENT_SHADER, code_fragment.data());
    shader_id   = glCreateProgram();

    // link compiled shaders in a single shader program
    glAttachShader(shader_id, vso_id);
    glAttachShader(shader_id, fso_id);
    glLinkProgram(shader_id);
    print_error(shader_id, GL_LINK_STATUS, false);
}

Shader::~Shader() noexcept
{
    glDeleteShader(vso_id);
    glDeleteShader(fso_id);

    deactivate();
    glDeleteProgram(shader_id);
}

void Shader::activate() const
{ glUseProgram(shader_id); }

void Shader::deactivate() const
{ glUseProgram(0); }

unsigned int Shader::get_id() const
{ return shader_id; }

int Shader::locate_attribute(std::string_view const& attrib_name) const
{ return glGetAttribLocation(shader_id, attrib_name.data()); }

int Shader::locate_uniform(std::string_view const& uniform_name) const
{ return glGetUniformLocation(shader_id, uniform_name.data()); }

bool Shader::isvalid_location(int loc, std::string_view const& varname) const
{
    if (loc < 0)
    {
        std::cerr << "FAILED: shader couldn't locate variable: " << varname << ".\n";
        return false;
    }

    return true;
}

unsigned int Shader::compile_shader(GLenum shader_type, char const* src_code) const
{
    unsigned int id = glCreateShader(shader_type);
    glShaderSource(id, 1, &src_code, nullptr);
    glCompileShader(id);
    print_error(id, GL_COMPILE_STATUS);
    return id;
}

void Shader::set1(std::string_view const& varname, int value) const
{
    int loc = locate_uniform(varname);
    if (isvalid_location(loc, varname))
        glUniform1i(loc, value);
}

void Shader::set1(std::string_view const& varname, float value) const
{
    int loc = locate_uniform(varname);
    if (isvalid_location(loc, varname))
        glUniform1f(loc, value);
}

void Shader::set1(std::string_view const& varname, uint32_t value) const
{
    int loc = locate_uniform(varname);
    if (isvalid_location(loc, varname))
        glUniform1ui(loc, value);
}

void Shader::set4x4(std::string_view const& varname, glm::mat4 const& mat, bool transpose) const
{
    int loc = locate_uniform(varname);
    if (isvalid_location(loc, varname))
        glUniformMatrix4fv(loc, 1, transpose, &mat[0][0]);
}

std::string Shader::read_file(std::string_view const& filepath) const
{
    std::string buffer;

    std::ifstream file;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        std::ostringstream streams;
        file.open(filepath);
        streams << file.rdbuf();
        buffer = streams.str();
    }
    catch (std::ifstream::failure err)
    {
        std::cerr << "ERROR: File couldn't be read properly \nFile location: " 
            << filepath << "\nerror message: \n" << err.what() << "\n";
    }

    return buffer;
}

void Shader::print_error(uint32_t id, GLenum type, bool shader) const
{
    int sucess_status;
    char infoLog[1024];

    if (shader)
    {
        glGetShaderiv(id, type, &sucess_status);
        if (!sucess_status)
        {
            glGetShaderInfoLog(id, 1024, nullptr, infoLog);
            std::string shader_type = (type == GL_VERTEX_SHADER) ? 
                "VERTEX SHADER" : "FRAGMENT SHADER";
            std::cerr << shader_type << " ERROR: \n" << infoLog << "\n"; 
        }
    }
    else
    {
        glGetProgramiv(id, type, &sucess_status);
        if (!sucess_status)
        {
            glGetProgramInfoLog(id, 1024, nullptr, infoLog);
            std::cerr << "SHADER PROGRAM ERROR: \n" << infoLog << "\n";
        }
    }
}

