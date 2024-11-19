#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string_view>

class Shader 
{
public:
    explicit Shader(std::string_view const& path_vertex, std::string_view const& path_fragment);
    ~Shader() noexcept;

    void            activate() const;
    void            deactivate() const;
    unsigned int    get_id() const;
    int             locate_attribute(std::string_view const& attrib_name) const;
    int             locate_uniform(std::string_view const& uniform_name) const;

    void            set1(std::string_view const& varname, int value) const;
    void            set1(std::string_view const& varname, float value) const;
    void            set1(std::string_view const& varname, uint32_t value) const;

    void            set4x4(std::string_view const& varname, glm::mat4 const& mat, bool transpose = false) const;

private:
    bool            isvalid_location(int loc, std::string_view const& varname) const;
    std::string     read_file(std::string_view const& filepath) const;
    unsigned int    compile_shader(GLenum shader_type, char const* src_code) const;
    void            print_error(unsigned int id, GLenum type, bool shader = true) const;

private:
    unsigned int shader_id;
    unsigned int vso_id;
    unsigned int fso_id;
};

