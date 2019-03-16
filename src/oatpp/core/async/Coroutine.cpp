/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#include "Coroutine.hpp"

namespace oatpp { namespace async {

const Action Action::_WAIT_RETRY(TYPE_WAIT_RETRY, nullptr, nullptr);
const Action Action::_REPEAT(TYPE_REPEAT, nullptr, nullptr);
const Action Action::_FINISH(TYPE_FINISH, nullptr, nullptr);
const Action Action::_ABORT(TYPE_ABORT, nullptr, nullptr);

Error::Error(const char* pMessage, bool pIsExceptionThrown = false)
  : message(pMessage)
  , isExceptionThrown(pIsExceptionThrown)
{}



Action::Action(v_int32 type,
       AbstractCoroutine* coroutine,
       FunctionPtr functionPtr)
  : m_type(type)
  , m_coroutine(coroutine)
  , m_functionPtr(functionPtr)
  , m_error(Error(nullptr))
{}

Action::Action(const Error& error)
  : m_type(TYPE_ERROR)
  , m_coroutine(nullptr)
  , m_functionPtr(nullptr)
  , m_error(error)
{}

bool Action::isError(){
  return m_type == TYPE_ERROR;
}

void Action::free() {
  if(m_coroutine != nullptr) {
    m_coroutine->free();
    m_coroutine = nullptr;
  }
}
  
}}
