#pragma once

#include <memory>
#include <list>
#include <unordered_map>

#include <boost/filesystem.hpp>

#include <rocketjoe/services/python_sandbox/detail/forward.hpp>
#include <rocketjoe/services/python_sandbox/detail/data_set.hpp>

namespace rocketjoe { namespace services { namespace python_sandbox { namespace detail {

                class context final {
                public:
                    context(file_manager &file_manager);

                    auto text_file(const std::string &path) -> intrusive_ptr<data_set>;

                    template <class DTYPE,class ...Args>
                    auto make_new_step(Args... args) {
                        boost::intrusive_ptr<DTYPE> ds (new DTYPE(std::forward<Args>(args)...));
                        pipeline_.push_back(ds);
                        return ds;
                    }

                private:
                    file_manager &file_manager_;
                    std::list<boost::intrusive_ptr<data_set>> pipeline_;
                };

}}}}