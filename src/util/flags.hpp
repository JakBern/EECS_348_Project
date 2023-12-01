// Contains all flags used in the main by the Arithmetic Expression Evaluator
//
// Enum flags should use the naming convention for constants from
// the Google C++ Style Guide, ie mixed case preceded by a k.
//
// Author(s): 
// Jake Bernard [from 10/17/2023 - Present]
//
//
// Last update:
//  - 11/30/2023 (Jake): Commented out unused flags
//    
//

#ifndef UTIL_FLAGS_H_
#define UTIL_FLAGS_H_


namespace flags {

  // Used in main as the return value from Interface.run().
  // Allows the main to decide between exiting the program,
  // or switching between different interfaces.
  enum class InterfaceCode {
    kCleanExit,
    kSwitchToGUI,
    kSwitchToTUI
  };

  // ===========REMOVED UNTIL FUTURE ITERATIONS==========

  // Returned by the parser when evaluating a function, along with the position
  // of an error. 
  //
  // The position returned alongside a divide by zero error should be at the
  // division operator which caused the error.
  // enum class EvalError {
  //   kSuccess,
  //   kDivByZero,
  //   kInvalidSyntax,
  //   kMismatchedParentheses
  // };

  // Used when creating a user variable.
  // - kSuccess signals success in creating the variable
  // - kOverwrite signals that the variable already exists
  //    and will be overwritten
  // - kFormatError means the user-defined variable uses illegal characters
  // - kReservedError means the user-defined variable matches a reserved keyword
  // enum class UserVarMsg {
  //   kVarWriteSuccess,
  //   kVarNeedOverwrite,
  //   kVarFormatError,
  //   kVarReservedError
  // };

  // =====================END REMOVED====================

}

#endif