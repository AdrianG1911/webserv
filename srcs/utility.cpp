/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:52:35 by hshimizu          #+#    #+#             */
/*   Updated: 2025/06/28 02:47:34 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftpp/exceptions/OSError.hpp>
#include <ftpp/string/string.hpp>

#include <cmath>
#include <limits>
#include <stdexcept>
#include <sys/fcntl.h>
#include <unistd.h>

std::size_t parseSize(std::string const &str) {
  if (str.empty() || !isdigit(str[0]))
    throw std::invalid_argument("invalid size");
  double size;
  std::size_t unit;
  {
    std::size_t pos;
    size = ftpp::stod(str, &pos);
    std::string tmp(str, pos, std::string::npos);
    if (tmp.empty())
      unit = 1;
    else if (tmp == "k" || tmp == "K")
      unit = 1ul << 10;
    else if (tmp == "m" || tmp == "M")
      unit = 1ul << 20;
    else if (tmp == "g" || tmp == "G")
      unit = 1ul << 30;
    else
      throw std::runtime_error("invalid size unit");
  }
  if (unit > std::numeric_limits<std::size_t>::max() / size)
    throw std::overflow_error("size overflow");
  return static_cast<std::size_t>(size * unit);
}

void setCloexec(int fd) {
  int flags;
  flags = fcntl(fd, F_GETFD);
  if (flags == -1)
    throw ftpp::OSError(errno, "fcntl");
  if (!(flags & FD_CLOEXEC)) {
    if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) == -1)
      throw ftpp::OSError(errno, "fcntl");
  }
}
