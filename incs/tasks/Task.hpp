/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Task.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:41:05 by hshimizu          #+#    #+#             */
/*   Updated: 2025/06/28 03:54:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Connection.hpp"

#include <ftpp/noncopyable/NonCopyable.hpp>

class Task : private ftpp::NonCopyable {
public:
  Connection::Cycle &cycle;

private:
  Task();

protected:
  Task(Connection::Cycle &cycle);

public:
  virtual ~Task();

  virtual void onData(std::vector<char> const &data) = 0;
  virtual void onEof() = 0;
};
