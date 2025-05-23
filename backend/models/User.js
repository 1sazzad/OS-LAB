const mongoose = require("mongoose");

const userSchema = new mongoose.Schema({
  username: { type: String, required: true, unique: true },
  password: { type: String, required: true },
  role: {
    type: String,
    enum: ["patient", "assistant", "doctor", "admin"],
    required: true,
  },
  userId: { type: mongoose.Schema.Types.ObjectId, refPath: "role" },
});

module.exports = mongoose.model("User", userSchema);
