let errorComponent = (index: int, error: string) : React.element => {
  <div key=string_of_int(index) className=ErrorsCSS.error>
    <div className=ErrorsCSS.errorTitle>
      {React.string("ERROR")}
    </div>
    <div className=ErrorsCSS.errorBody>
      {React.string(error)}
    </div>
  </div>
};

[@react.component]
let make = (~errors: list(string)) => {
  <div className=ErrorsCSS.errorContainer>
    { ComponentHelper.renderList(errors, errorComponent);}
  </div>
};