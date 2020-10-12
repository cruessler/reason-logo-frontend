@bs.val external document: {..} = "document"

let style = document["createElement"]("style")
document["head"]["appendChild"](style)
style["innerHTML"] = Styles.style

ReactDOMRe.render(
  <React.StrictMode> <App /> </React.StrictMode>,
  document["getElementById"]("root"),
)
