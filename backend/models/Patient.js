const mongoose = require("mongoose");

const patientSchema = new mongoose.Schema({
  userId: { type: mongoose.Schema.Types.ObjectId, ref: "User", required: true },
  name: { type: String, required: true },
  contact: { type: String, required: true },
  medicalHistory: [String],
  billingInfo: Object,
});

module.exports = mongoose.model("Patient", patientSchema);
